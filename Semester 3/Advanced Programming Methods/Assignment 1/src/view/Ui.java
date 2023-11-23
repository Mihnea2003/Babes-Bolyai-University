package view;
import controller.Controller;
import model.Bicycle;
import model.Car;
import model.Motorcycle;
import model.Vehicle;
import java.util.List;
import java.util.Scanner;

public class Ui {
    private Controller controller;

    public Ui(Controller controller)
    {
        this.controller = controller;
    }

    public void printMenu()
    {
        System.out.println("1.Populate");
        System.out.println("2.Add");
        System.out.println("3.Remove");
        System.out.println("4.Print");
        System.out.println("5.Filter");
        System.out.println("0.Exit");
    }

    public void run()
    {
        int choice = 0;
        Scanner sc = new Scanner(System.in);
        do{
            printMenu();
            choice = sc.nextInt();
            switch(choice)
            {
                default:
                    System.out.println("error");
                    break;
                case 0:
                    break;
                case 1:
                    controller.add("Car","rosu");
                    controller.add("Bicycle","rosu");
                    controller.add("Motorcycle","verde");
                    System.out.println("Added vehicles!");
                    break;
                case 5:
                    Scanner scanner = new Scanner(System.in);
                    System.out.println("What colour do you want to filter?");
                    String colour = scanner.nextLine();
                    List<Vehicle> result = controller.filterrepo(colour);
                    for(Vehicle v : result)
                    {
                        System.out.println(v.toString());
                    }
                    System.out.println("Filtered items");
                    break;
                case 4:
                    Vehicle[] all = controller.getAll();
                    for (Vehicle v : all){
                        if (v!=null){
                        System.out.println((v.toString()));}
                    }
                    break;
                case 2:
                    Scanner scann = new Scanner(System.in);
                    System.out.println("What type of vehicle?");
                    String type = scann.nextLine();
                    Scanner scan = new Scanner(System.in);
                    System.out.println("What colour do you want your vehicle to be?");
                    String col = scan.nextLine();
                    try {
                        if (col.isEmpty()) {
                            throw new IllegalArgumentException("You need to say a colour");
                        }else{
                            controller.add(type,col);
                        }
                    }catch (IllegalArgumentException e) {
                        System.out.println("You need to say a colour");
                    }
                    break;
                case 3:
                    Scanner scan1 = new Scanner(System.in);
                    System.out.println("What type of vehicle?");
                    String type1 = scan1.nextLine();
                    Scanner scan2 = new Scanner(System.in);
                    System.out.println("What colour do you want your vehicle to be?");
                    String col1 = scan2.nextLine();
                    controller.remove(type1,col1);
                    break;
            }
        }while(choice != 0);

        sc.close();
    }
}
