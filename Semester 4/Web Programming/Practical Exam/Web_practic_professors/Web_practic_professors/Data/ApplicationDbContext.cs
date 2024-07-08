using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_professors.Models;

namespace Web_practic_professors.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Person> Persons { get; set; }
        public DbSet<Course> Courses { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed initial data
            modelBuilder.Entity<Person>().HasData(
                new Person { Id = 1, Name = "Professor John", Role = "professor" },
                new Person { Id = 2, Name = "Student Alice", Role = "student" },
                new Person { Id = 3, Name = "Student Bob", Role = "student" }
            );

            modelBuilder.Entity<Course>().HasData(
                new Course { Id = 1, ProfessorId = 1, CourseName = "Computer Science 101", Participants = "2,3", Grades = "2:3,3:4" },
                new Course { Id = 2, ProfessorId = 1, CourseName = "Mathematics 101", Participants = "3", Grades = "3:5" }
            );
        }
    }
}
