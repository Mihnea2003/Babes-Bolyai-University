import repository.InMemoryRepository;
import view.Ui;
import controller.Controller;

public class Main {
    public static void main(String[] args) {
        Ui ui = new Ui(new Controller(new InMemoryRepository()));
        ui.run();
    }
}