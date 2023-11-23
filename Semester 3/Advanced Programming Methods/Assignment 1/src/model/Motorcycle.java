package model;

public class Motorcycle implements Vehicle{
    private String colour ;

    public Motorcycle() {this.colour = "";}
    public Motorcycle(String colour){this.colour = colour;}

    @Override
    public String getColour(){return this.colour;}

    @Override
    public String toString(){return "Motorcycle with the colour: "+this.colour;}
}
