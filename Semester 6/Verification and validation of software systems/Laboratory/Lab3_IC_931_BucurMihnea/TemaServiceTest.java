import domain.Tema;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import repository.StudentXMLRepository;
import repository.TemaXMLRepository;
import repository.NotaXMLRepository;
import service.Service;
import validation.TemaValidator;
import validation.ValidationException;

import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

class TemaServiceTest {
    private StudentXMLRepository studentRepo;
    private TemaXMLRepository temaRepo;
    private NotaXMLRepository notaRepo;
    private Service service;

    @BeforeEach
    void setUp() {
        studentRepo = mock(StudentXMLRepository.class);
        temaRepo = mock(TemaXMLRepository.class);
        notaRepo = mock(NotaXMLRepository.class);
        service = new Service(studentRepo, temaRepo, notaRepo);
    }

    @Test
    void testAddAssignment_Valid() {
        Tema tema = new Tema("1", "Homework", 4, 2);
        when(temaRepo.save(any(Tema.class))).thenReturn(null);
        int result = service.saveTema("1", "Homework", 4, 2);
        assertEquals(1, result, "Expected success for valid assignment");
    }

    @Test
    void testAddAssignment_EmptyID() {
        assertThrows(ValidationException.class, () -> {
            new TemaValidator().validate(new Tema("", "Homework", 4, 2));
        });
    }


}
