package repository;
import model.Vehicle;
public interface IRepository {
    void add(Vehicle v);
    void remove(Vehicle v);
    Vehicle[] getAll();
    int size();
}
