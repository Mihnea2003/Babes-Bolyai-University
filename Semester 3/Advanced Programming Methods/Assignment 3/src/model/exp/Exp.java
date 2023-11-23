package model.exp;

import model.MyException;
import model.ADT.MyIDictionary;
import model.type.Type;
import model.value.Value;

public interface Exp {
    Value eval(MyIDictionary<String, Value> tbl) throws MyException;

}