using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_journals.Models;

namespace Web_practic_journals.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Journal> Journals { get; set; }
        public DbSet<Article> Articles { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed Journals
            modelBuilder.Entity<Journal>().HasData(
                new Journal { Id = 3, Name = "Journal 3" }
            );

            // Seed Articles
            modelBuilder.Entity<Article>().HasData(
                new Article { Id = 1, User = "User 1", JournalId = 1, Summary = "Summary 1", Date = DateTime.Now },
                new Article { Id = 2, User = "User 1", JournalId = 2, Summary = "Summary 2", Date = DateTime.Now },
                new Article { Id = 3, User = "User 2", JournalId = 1, Summary = "Summary 3", Date = DateTime.Now },
                new Article { Id = 4, User = "User 2", JournalId = 3, Summary = "Summary 4", Date = DateTime.Now }
            );
        }
    }
}
