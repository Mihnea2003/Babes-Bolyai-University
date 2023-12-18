package model.ADT;
import model.value.Value;
import java.util.HashMap;

public interface MyIHeap<K,V> {
    void put(K key, V value);
    V get(K key);
    boolean isDefined(K key);
    void update(K key, V value);
    int getFreeAddress();
    void setContent(HashMap<K, V> newHeap);
    HashMap<K, V> getContent();
}
