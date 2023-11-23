package model.exp;

import model.MyException;
import model.ADT.MyIDictionary;
import model.type.Type;
import model.value.Value;

public class VarExp implements Exp {
    private String id;

    public VarExp(String id) {
        this.id = id;
    }

    public String getId() {
        return id;
    }

    public void setId(String id) {
        this.id = id;
    }

    @Override
    public Value eval(MyIDictionary<String, Value> tbl) throws MyException {
        return tbl.lookup(id);
    }


    @Override
    public String toString() {
        return "VarExp{" +
                "id='" + id + '\'' +
                '}';
    }
}