package model.exp;
import model.ADT.MyIDictionary;
import model.MyException;
import model.type.Type;
import model.value.Value;
import model.ADT.MyIHeap;
public interface Exp {
    Value eval(MyIDictionary<String,Value> symTbl,MyIHeap<Integer,Value> heap) throws MyException;
}
