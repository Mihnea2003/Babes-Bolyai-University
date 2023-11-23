package model;

public class Bicycle implements Vehicle{
    private String colour ;

    public Bicycle() {this.colour = "";}
    public Bicycle(String colour){this.colour = colour;}

    @Override
    public String getColour(){return this.colour;}

    @Override
    public String toString(){return "Bicycle with the colour: "+this.colour;}
}
