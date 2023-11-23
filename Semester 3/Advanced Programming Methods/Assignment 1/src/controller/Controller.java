package controller;

import model.Bicycle;
import model.Motorcycle;
import repository.IRepository;
import model.Vehicle;
import model.Car;
import java.util.ArrayList;
import java.util.List;

public class Controller {
    IRepository repository;

    public Controller(IRepository repository)
    {
        this.repository = repository;
    }

    public void add(String type,String colour)
    {
       try {
           if (type.equals("Car")) {
               repository.add(new Car(colour));
           }else {
               if (type.equals("Bicycle")) {
                   repository.add(new Bicycle(colour));
               }else {
                   if (type.equals("Motorcycle")) {
                       repository.add(new Motorcycle(colour));
                   }
                   else{
                       throw new IllegalArgumentException("Vehicle with the wrong attributes want to be added.");
                   }
               }
           }
       }catch (IllegalArgumentException e) {
           System.out.println("Vehicle already in the list or wrong attributes.");
       }
    }
    public void remove(String type,String colour)
    {
       try {
           if (type.equals("Car")) {
               repository.remove(new Car(colour));
           }
           if (type.equals("Bicycle")) {
               repository.remove(new Bicycle(colour));
           }
           if (type.equals("Motorcycle")) {
               repository.remove(new Motorcycle(colour));
           }
       }catch (IllegalArgumentException e) {
           System.out.println("Vehicle not found . Vehicle not removed.");
       }
    }
    public Vehicle[] getAll()
    {
        return repository.getAll();
    }

    public List<Vehicle> filterrepo(String colour)
    {
        List<Vehicle> result = new ArrayList<>();
        Vehicle[] all = repository.getAll();
        for(Vehicle v: all)
        {
            if(v!=null) {
                if (v.getColour().equals(colour))
                    result.add(v);
            }
        }
        return result;
    }
}
