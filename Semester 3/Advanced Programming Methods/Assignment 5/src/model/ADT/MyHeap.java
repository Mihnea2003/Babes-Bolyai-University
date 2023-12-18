package model.ADT;
import model.value.Value;
import java.util.HashMap;

public class MyHeap<K,V> implements MyIHeap<K,V>{
    private HashMap<K, V> heapTable;
    private int freeLocation;
    public MyHeap(){
        heapTable = new HashMap<K, V>();
        freeLocation = 0;
    }
    public void setFreeLocation(int freeLocation){
        this.freeLocation = freeLocation;
    }
    @Override
    public void put(K key, V value){
        heapTable.put((K)key, (V)value);
    }
    @Override
    public V get(K key){
        return heapTable.get(key);
    }
    @Override
    public boolean isDefined(K key){
        return heapTable.containsKey(key);
    }
    @Override
    public void update(K key,V value){
        heapTable.put(key, value);
    }
    @Override
    public int getFreeAddress(){
        freeLocation++;
        return freeLocation;
    }
    @Override
    public void setContent(HashMap<K, V> newHeap){
        heapTable = (HashMap<K, V>) newHeap;
    }
    @Override
    public HashMap<K, V> getContent(){
        return heapTable;
    }
    @Override
    public String toString(){
        StringBuilder result = new StringBuilder("MyHeap{\n");
        for (HashMap.Entry<K, V> entry : heapTable.entrySet()) {
            result.append("\t").append(entry.getKey()).append(": ").append(entry.getValue()).append("\n");
        }
        result.append("}");
        return result.toString();
    }
}
