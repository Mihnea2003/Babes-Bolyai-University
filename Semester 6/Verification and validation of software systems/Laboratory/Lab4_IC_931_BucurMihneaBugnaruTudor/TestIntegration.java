import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.NotaXMLRepository;
import repository.StudentXMLRepository;
import repository.TemaXMLRepository;
import service.Service;
import validation.NotaValidator;
import validation.StudentValidator;
import validation.TemaValidator;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class TestIntegration {

    private Service service;

    @BeforeEach
    public void setup() {
        StudentValidator studentValidator = new StudentValidator();
        TemaValidator temaValidator = new TemaValidator();
        NotaValidator notaValidator = new NotaValidator();

        StudentXMLRepository studentRepo = new StudentXMLRepository(studentValidator, "d:\\UBB\\Semester_6\\Software Validation\\ssvv_lab2_bugnaru_bucur\\studentsTest.xml");
        TemaXMLRepository temaRepo = new TemaXMLRepository(temaValidator, "d:\\UBB\\Semester_6\\Software Validation\\ssvv_lab2_bugnaru_bucur\\assignmentsTest.xml");
        NotaXMLRepository notaRepo = new NotaXMLRepository(notaValidator, "d:\\UBB\\Semester_6\\Software Validation\\ssvv_lab2_bugnaru_bucur\\gradesTest.xml");

        service = new Service(studentRepo, temaRepo, notaRepo);
    }

    @Test
    public void testUnitAddStudent() {
        int result = service.saveStudent("4", "Bob", 934);
        assertEquals(0, result, "Expected success when adding a valid student");
    }

    @Test
    public void testUnitAddAssignment() {
        int result = service.saveTema("4", "Assignment 4", 13, 8);
        assertEquals(0, result, "Expected success when adding a valid assignment");
    }

    @Test
    public void testUnitAddGrade() {
        service.saveStudent("5", "Charlie", 935);
        service.saveTema("5", "Assignment 5", 11, 9);

        int result = service.saveNota("5", "5", 7.5, 10, "Needs improvement");
        assertEquals(0, result, "Expected success when adding a valid grade");
    }

    @Test
    public void testIntegrationAllFeatures() {
        // Add a student
        service.saveStudent("3", "Alice", 933);

        // Add an assignment
        service.saveTema("3", "Assignment 3", 14, 7);

        // Add a grade
        int result = service.saveNota("3", "3", 10, 14, "Excellent");
        assertEquals(0, result, "Expected success when integrating all features");
    }
}