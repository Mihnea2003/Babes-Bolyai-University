package model;

public class Car implements Vehicle{
    private String colour ;

    public Car() {this.colour = "";}
    public Car(String colour){this.colour = colour;}

    @Override
    public String getColour(){return this.colour;}

    @Override
    public String toString(){return "Car with the colour: "+this.colour;}
}
