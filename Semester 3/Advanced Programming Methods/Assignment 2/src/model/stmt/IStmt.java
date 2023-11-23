package model.stmt;

import model.MyException;
import model.PrgState;

public interface IStmt {
    public PrgState execute(PrgState state) throws MyException;

}