package model;

import model.ADT.*;
import model.stmt.IStmt;
import model.value.Value;
import java.io.BufferedReader;

public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    IStmt originalProgram;
    IFileTable<String, BufferedReader> fileTable;
    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot,
                    IFileTable<String, BufferedReader> fileTable,IStmt prg){
        exeStack=stk;
        symTable=symtbl;
        this.fileTable = fileTable;
        out = ot;
        originalProgram=prg;
        stk.push(prg);
    }

    @Override
    public String toString() {
        return "PrgState{" +
                "exeStack=" + exeStack +
                ", symTable=" + symTable +
                ", out=" + out +
                ",fileTable=" + fileTable +
                '}';
    }

    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }
    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }
    public IFileTable<String, BufferedReader> getFileTable() {
        return fileTable;
    }
    public MyIList<Value> getOut() {
        return out;
    }

    public void setExeStack(MyIStack<IStmt> exeStack) {
        this.exeStack = exeStack;
    }

    public void setSymTable(MyIDictionary<String, Value> symTable) {
        this.symTable = symTable;
    }

    public void setFileTable(IFileTable<String, BufferedReader> fileTable) {
        this.fileTable = fileTable;
    }
    public void setOut(MyIList<Value> out) {
        this.out = out;
    }
    public boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }
    public PrgState oneStep() throws Exception {
        if(exeStack.isEmpty()) throw new Exception("Program state stack is empty");
        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }
    public IStmt getOriginalProgram() {
        return originalProgram;
    }
}
