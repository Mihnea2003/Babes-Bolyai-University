package model.stmt;
import model.MyException;
import model.PrgState;
import model.ADT.MyIDictionary;
import model.ADT.MyIStack;
import model.ADT.MyStack;
import model.type.Type;


public class ForkStatement implements IStmt{
    private IStmt statement;

    public ForkStatement(IStmt statement) {
        this.statement = statement;
    }

    @Override
    public PrgState execute(PrgState state) throws MyException {
        MyIStack<IStmt> newStack = new MyStack<IStmt>();
        return new PrgState(newStack, state.getSymTable().deepCopy(), state.getOut(), state.getFileTable(),
                statement, state.getHeap());
    }

    @Override
    public String toString() {
        return "fork(" + statement.toString() + ")";
    }
}
