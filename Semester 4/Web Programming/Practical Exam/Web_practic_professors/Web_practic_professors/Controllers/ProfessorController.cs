using Microsoft.AspNetCore.Mvc;
using System.Linq;
using System.Threading.Tasks;
using Web_practic_professors.Data;

public class ProfessorController : Controller
{
    private readonly ApplicationDbContext _context;

    public ProfessorController(ApplicationDbContext context)
    {
        _context = context;
    }

    public IActionResult Index()
    {
        return View();
    }

    [HttpPost]
    public IActionResult Index(string professorName)
    {
        var professor = _context.Persons.FirstOrDefault(p => p.Name == professorName && p.Role == "professor");
        if (professor != null)
        {
            return RedirectToAction("Courses", new { professorId = professor.Id });
        }
        return View();
    }

    public IActionResult Courses(int professorId)
    {
        var courses = _context.Courses.Where(c => c.ProfessorId == professorId).ToList();
        ViewBag.ProfessorId = professorId;
        return View(courses);
    }

    public IActionResult Participants(int courseId)
    {
        var course = _context.Courses.FirstOrDefault(c => c.Id == courseId);
        if (course != null)
        {
            var participants = course.Participants?.Split(',') ?? new string[0];
            var participantsList = _context.Persons.Where(p => participants.Contains(p.Id.ToString())).ToList();
            return View(participantsList);
        }
        return NotFound();
    }

    public IActionResult StudentCourses(int studentId)
    {
        var courses = _context.Courses.Where(c => c.Participants.Contains(studentId.ToString())).ToList();
        return View(courses);
    }

    [HttpPost]
    public IActionResult AssignGrade(int courseId, int studentId, int grade)
    {
        var course = _context.Courses.FirstOrDefault(c => c.Id == courseId);
        if (course != null)
        {
            var participants = course.Participants?.Split(',').ToList() ?? new List<string>();
            var grades = course.Grades?.Split(',').ToList() ?? new List<string>();

            if (!participants.Contains(studentId.ToString()))
            {
                participants.Add(studentId.ToString());
                course.Participants = string.Join(",", participants);
            }

            var gradeEntry = grades.FirstOrDefault(g => g.StartsWith(studentId.ToString() + ":"));
            if (gradeEntry != null)
            {
                grades.Remove(gradeEntry);
            }
            grades.Add($"{studentId}:{grade}");
            course.Grades = string.Join(",", grades);

            _context.SaveChanges();
            return RedirectToAction("Participants", new { courseId });
        }
        return NotFound();
    }
}
