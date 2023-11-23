package repository;

import model.MyException;
import model.PrgState;

import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

public class Repository implements IRepository{
    private List<PrgState> programStates;
    private String logFilePath;

    public Repository(List<PrgState> programStates, String logFilePath) {
        this.programStates = programStates;
        this.logFilePath = logFilePath;
    }

    public String getLogFilePath() {
        return logFilePath;
    }

    public void setLogFilePath(String logFilePath) {
        this.logFilePath = logFilePath;
    }
    @Override
    public PrgState getCrtPrg() {
        return this.programStates.get(0);
    }
    @Override
    public void logPrgStateExec(PrgState program) throws MyException {
        try {
            PrintWriter logFile = new PrintWriter(new BufferedWriter(new FileWriter(logFilePath, true)));
            logFile.println("**");
            logFile.println("~ExeStack~~");
            logFile.println(program.getExeStack().toString());
            logFile.println("~~SymbolTable~~");
            logFile.println(program.getSymTable().toString());
            logFile.println("~~Output~~");
            logFile.println(program.getOut().toString());
            logFile.println("~~FileTable~");
            logFile.println(program.getFileTable().toString());
            logFile.println("**");
            logFile.println("\n");
            logFile.close();
        } catch (IOException e) {
            throw new MyException("Error writing to log file");
        }
    }
    @Override
    public List<PrgState> getPrgList() {
        return this.programStates;
    }

}