import domain.Student;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;
import repository.StudentXMLRepository;
import repository.NotaXMLRepository;
import repository.TemaXMLRepository;
import service.Service;

class StudentServiceTest {
    private StudentXMLRepository studentXmlRepo;
    private TemaXMLRepository temaXmlRepo;
    private NotaXMLRepository notaXmlRepo;
    private Service studentService;

    @BeforeEach
    void setUp() {
        studentXmlRepo = mock(StudentXMLRepository.class);
        studentService = new Service(studentXmlRepo,temaXmlRepo,notaXmlRepo);
    }

    @Test
    void testSaveStudent_InvalidName() {
        int result2 = studentService.saveStudent("123", "", 101);
        assertEquals(0, result2, "Expected failure when name is empty");

        when(studentXmlRepo.save(any(Student.class))).thenReturn(null);
        int result3 = studentService.saveStudent("123", "John Doe", 101);
        assertEquals(1, result3, "Expected success when name is valid");
    }
    @Test
    void testSaveStudent_InvalidGroup() {
        int result1 = studentService.saveStudent("456", "Alice", -1);
        assertEquals(0, result1, "Expected failure when group number is negative");
    }

    @Test
    void testSaveStudent_ValidStudent() {
        when(studentXmlRepo.save(any(Student.class))).thenReturn(null);

        int result = studentService.saveStudent("101", "Charlie", 302);
        assertEquals(1, result, "Expected success when all parameters are valid");
    }
}