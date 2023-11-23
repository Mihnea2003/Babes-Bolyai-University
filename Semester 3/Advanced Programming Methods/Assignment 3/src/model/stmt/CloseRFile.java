package model.stmt;

import model.ADT.IFileTable;
import model.ADT.MyIDictionary;
import model.ADT.MyIStack;
import model.MyException;
import model.PrgState;
import model.exp.Exp;
import model.type.StringType;
import model.type.Type;
import model.value.StringValue;
import model.value.Value;

import java.io.BufferedReader;
import java.io.IOException;

public class CloseRFile implements IStmt{

    private Exp exp;

    public CloseRFile(Exp exp) {
        this.exp = exp;
    }

    public Exp getExp() {
        return exp;
    }

    public void setExp(Exp exp) {
        this.exp = exp;
    }

    @Override
    public String toString() {
        return "CloseRFile{" +
                "exp=" + exp +
                '}';
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> stk = state.getExeStack();
        MyIDictionary<String, Value> symTable = state.getSymTable();
        IFileTable<String, BufferedReader> fileTable = state.getFileTable();

        Value val = exp.eval(symTable);
        if (val.getType().equals(new StringType())) {
            StringValue strVal = (StringValue) val;
            String file = strVal.getVal();
            BufferedReader f = fileTable.lookup(file);
            try {
                f.close();
            } catch (IOException ex) {
                System.out.println("File " + file + " cannot be closed!");
            }
            fileTable.delete(file);
        }
        else {
            throw new MyException("Invalid type!");
        }

        return null;
    }
}