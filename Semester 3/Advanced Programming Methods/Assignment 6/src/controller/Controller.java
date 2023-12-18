package controller;
import model.ADT.MyIList;
import model.value.RefValue;
import model.value.Value;
import repository.IRepository;
import model.MyException;
import model.PrgState;
import model.ADT.MyIStack;
import model.stmt.IStmt;

import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.*;
import java.util.stream.Collectors;


public class Controller {
    private final IRepository repository;
    private ExecutorService executor;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public IRepository getRepository() {
        return repository;
    }

    public MyIList<Value> getOut(PrgState state) {
        return state.getOut();
    }

    public List<Integer> getAddrFromSymTable(Collection<Value> symTableValues) {
        return symTableValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> ((RefValue) v).getAddress())
                .collect(Collectors.toList());
    }

    private List<Integer> getAddrFromHeap(Collection<Value> heapValues) {
        return heapValues.stream()
                .filter(v -> v instanceof RefValue)
                .map(v -> ((RefValue) v).getAddress())
                .collect(Collectors.toList());
    }

    private HashMap<Integer, Value> safeGarbageCollector(List<Integer> symTableAddr, Map<Integer, Value> heap) {
        List<Integer> heapAddr = getAddrFromHeap(heap.values());
        return heap.entrySet().stream()
                .filter(e -> (symTableAddr.contains(e.getKey()) || heapAddr.contains(e.getKey())))
                .collect(Collectors.toMap(Map.Entry::getKey, Map.Entry::getValue, (v1, v2) -> v2, HashMap::new));
    }

    private synchronized List<PrgState> removeCompletedPrograms(List<PrgState> inPrgList) {
        return inPrgList.stream()
                .filter(PrgState::isNotCompleted)
                .collect(Collectors.toList());
    }

    public synchronized void oneStepForAllPrograms(List<PrgState> programList) throws InterruptedException {
        programList.forEach(prg -> {
            try {
                repository.logPrgStateExec(prg);
            } catch (MyException e) {
                throw new RuntimeException(e);
            }
        });

        List<Callable<PrgState>> callList = programList.stream()
                .filter(p -> !p.getExeStack().isEmpty())
                .map(p -> (Callable<PrgState>) (() -> {
                    if (!p.getExeStack().isEmpty()) {
                        return p.oneStep();
                    } else {
                        return p;
                    }
                }))
                .collect(Collectors.toList());

        List<PrgState> newProgramList = executor.invokeAll(callList).stream()
                .map(future -> {
                    try {
                        return future.get();
                    } catch (InterruptedException | ExecutionException e) {
                        throw new RuntimeException(e.getMessage());
                    }
                })
                .filter(p -> p != null)
                .collect(Collectors.toList());

        programList.addAll(newProgramList);

        programList.forEach(prg -> {
            try {
                repository.logPrgStateExec(prg);
            } catch (MyException e) {
                throw new RuntimeException(e);
            }
        });

        repository.setPrgList(programList);
    }

    public synchronized void allStep() throws InterruptedException {
        executor = Executors.newFixedThreadPool(2);

        List<PrgState> programList;
        synchronized (this) {
            programList = removeCompletedPrograms(repository.getPrgList());
        }

        while (!programList.isEmpty()) {
            synchronized (this) {
                programList.forEach(prg -> prg.getHeap().setContent(safeGarbageCollector(getAddrFromSymTable(prg.getSymTable().getContent().values()), prg.getHeap().getContent())));
                oneStepForAllPrograms(programList);
                programList = removeCompletedPrograms(repository.getPrgList());
            }
        }

        executor.shutdown();
        executor.awaitTermination(Long.MAX_VALUE, TimeUnit.NANOSECONDS);

        synchronized (this) {
            repository.setPrgList(programList);
        }
    }

}
