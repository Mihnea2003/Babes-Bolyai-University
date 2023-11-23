package repository;

import model.PrgState;
import model.MyException;

import java.util.List;

public interface IRepository {
    public List<PrgState> getPrgList();

    PrgState getCrtPrg();


    public void logPrgStateExec(PrgState p) throws MyException;
}
