

import domain.Tema;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import repository.TemaXMLRepository;
import service.Service;
import validation.TemaValidator;
import validation.ValidationException;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class TestAddAssignment {

    private TemaXMLRepository temaFileRepository;
    private TemaValidator temaValidator;
    private Service service;

    @BeforeAll
    static void createXML() {
        File xml = new File("temeTest.xml");
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(xml))) {
            writer.write("<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n" +
                    "<inbox>\n" +
                    "\n" +
                    "</inbox>");
            writer.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @BeforeEach
    public void setup() {
        this.temaValidator = new TemaValidator();
        this.temaFileRepository = new TemaXMLRepository(temaValidator,"temeTest.xml");
        this.service = new Service(null, this.temaFileRepository, null);
    }

    @AfterAll
    static void removeXML() {
        new File("temeTest.xml").delete();
    }

    // TC 1
    @Test
    void testAddAssignmentEmptyID() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("", "a", 1, 1);
            temaValidator.validate(tema);
            service.saveTema("", "a", 1, 1);
        });
    }

    // TC 2
    @Test
    void testAddAssignmentNullID() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema(null, "a", 1, 1);
            temaValidator.validate(tema);
            service.saveTema(null, "a", 1, 1);
        });
    }

    // TC 3
    @Test
    void testAddAssignmentEmptyDescription() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("1", "", 1, 1);
            temaValidator.validate(tema);
            service.saveTema("1", "", 1, 1);
        });
    }

    // TC 4
    @Test
    void testAddAssignmentDeadlineTooLarge() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("1", "a", 15, 1);
            temaValidator.validate(tema);
            service.saveTema("1", "a", 15, 1);
        });
    }

    // TC 5
    @Test
    void testAddAssignmentDeadlineTooSmall() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("1", "a", 0, 1);
            temaValidator.validate(tema);
            service.saveTema("1", "a", 0, 1);
        });
    }

    // TC 6
    @Test
    void testAddAssignmentReceivedTooSmall() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("1", "a", 1, 0);
            temaValidator.validate(tema);
            service.saveTema("1", "a", 1, 0);
        });
    }

    // TC 7
    @Test
    void testAddAssignmentReceivedTooLarge() {
        assertThrows(ValidationException.class, () -> {
            Tema tema = new Tema("1", "a", 1, 15);
            temaValidator.validate(tema);
            service.saveTema("1", "a", 1, 15);
        });
    }

    // TC 8
    @Test
    void testAddAssignmentValidAssignment() {
        Tema newTema = new Tema("1", "a", 1, 1);
        this.service.saveTema("1", "a", 1, 1);
        assertEquals(this.service.findAllTeme().iterator().next(), newTema);
    }
}
