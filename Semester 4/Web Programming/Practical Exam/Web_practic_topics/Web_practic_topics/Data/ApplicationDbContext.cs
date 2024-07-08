using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_topics.Models;

namespace Web_practic_topics.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Topic> Topics { get; set; }
        public DbSet<Post> Posts { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
    }
}
