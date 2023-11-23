package repository;
import model.Vehicle;
public class InMemoryRepository implements IRepository{
    private Vehicle[] vehicles;
    private int size;

    public InMemoryRepository()
    {
        vehicles = new Vehicle[100];
        size = 0;
    }

    @Override
    public void add(Vehicle v)
    {
        for (int i = 0; i < size; i++) {
            if (vehicles[i] != null && vehicles[i].toString().equals(v.toString())) {
                throw new IllegalArgumentException("Vehicle with the same attributes already exists.");
            }
        }
        vehicles[size++] = v;
    }

    @Override
    public void remove(Vehicle v)
    {
        int index = -1;
        for (int i = 0; i < size; i++) {
            if (vehicles[i] != null && vehicles[i].toString().equals(v.toString())) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            throw new IllegalArgumentException("Vehicle not found.");
        }
        if (index != -1) {
            for (int i = index; i < size - 1; i++) {
                vehicles[i] = vehicles[i + 1];
            }
            vehicles[size - 1] = null;
            size--;
        }
    }

    @Override
    public Vehicle[] getAll()
    {
        return this.vehicles;
    }

    public int size()
    {
        return this.size;
    }
}
