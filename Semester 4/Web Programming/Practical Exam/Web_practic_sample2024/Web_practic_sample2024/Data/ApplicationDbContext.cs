using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_sample2024.Models;

namespace Web_practic_sample2024.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<SoftwareDeveloper> SoftwareDevelopers { get; set; }
        public DbSet<Project> Projects { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
    }
}
