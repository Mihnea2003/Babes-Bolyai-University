using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Examen.Models;

namespace Examen.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        public DbSet<Examen.Models.Author> Author { get; set; }
        public DbSet<Examen.Models.Document> Document { get; set; }
        public DbSet<Examen.Models.Movie> Movie { get; set; }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed Flights
            modelBuilder.Entity<Author>().HasData(
                new Author { Id = 1, Name = "Bucur Mihnea", documentList = "document", movieList = "film" },
                new Author { Id = 2, Name = "Mada", documentList = "document,document2", movieList = "film,film2" },
                new Author { Id = 3 , Name="Mihnea",documentList = "document",movieList = "film"}

            );    
        }
    }
}
