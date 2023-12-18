package model;

import model.ADT.*;
import model.stmt.IStmt;
import model.value.Value;
import java.io.BufferedReader;
import java.io.PrintWriter;


public class PrgState {
    MyIStack<IStmt> exeStack;
    MyIDictionary<String, Value> symTable;
    MyIList<Value> out;
    MyIFileTable<String, BufferedReader> fileTable;
    IStmt originalProgram; //optional field, but good to have
    MyIHeap<Integer,Value> heap;

    private int id;
    private static int idCounter = 0;

    public PrgState(MyIStack<IStmt> stk, MyIDictionary<String, Value> symtbl, MyIList<Value> ot,MyIFileTable<String,BufferedReader> fileTable ,IStmt prg,MyIHeap<Integer,Value> heap){
        exeStack=stk;
        symTable=symtbl;
        out = ot;
        this.heap = heap;
        originalProgram=prg;
        this.fileTable = fileTable;
        stk.push(prg);
        id = getNewId();
    }

    @Override
    public String toString() {
        return "PrgState{" + "\n" +
                "id=" + id + "\n" +
                "exeStack=" + exeStack + "\n" +
                ", symTable=" + symTable + "\n" +
                ", out=" + out + "\n" +
                ", fileTable=" + fileTable + "\n" +
                ", heap=" + heap + "\n" +
                '}';
    }

    public int getId() {
        return id;
    }
    public int getNewId() {
        idCounter++;
        return idCounter;
    }
    public MyIHeap<Integer,Value> getHeap() {
        return heap;
    }
    public MyIStack<IStmt> getExeStack() {
        return exeStack;
    }
    public MyIDictionary<String, Value> getSymTable() {
        return symTable;
    }
    public MyIList<Value> getOut() {
        return out;
    }
    public MyIFileTable<String, BufferedReader> getFileTable() {
        return fileTable;
    }

    public void setHeap(MyIHeap<Integer,Value> heap) {
        this.heap = heap;
    }
    public Boolean isNotCompleted(){
        return !exeStack.isEmpty();
    }
    public PrgState oneStep() throws Exception {
        if(exeStack.isEmpty()) {
            throw new Exception("Error in PrgState.oneStep(): Execution stack is empty. Program may have completed or encountered an unexpected end.");
        }

        IStmt crtStmt = exeStack.pop();
        return crtStmt.execute(this);
    }

}
