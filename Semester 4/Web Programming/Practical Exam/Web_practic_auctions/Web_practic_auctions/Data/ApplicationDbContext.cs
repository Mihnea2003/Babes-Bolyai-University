using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_auctions.Models;

namespace Web_practic_auctions.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Category> Categories { get; set; }
        public DbSet<Auction> Auctions { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed some initial categories
            modelBuilder.Entity<Category>().HasData(
                new Category { Id = 1, Name = "Electronics" },
                new Category { Id = 2, Name = "Books" },
                new Category { Id = 3, Name = "Clothing" }
                // Add more categories as needed
            );

            // Seed some initial auctions
            modelBuilder.Entity<Auction>().HasData(
                new Auction { Id = 1, User = "user1", CategoryID = 1, Description = "Smartphone", Date = DateTime.Now },
                new Auction { Id = 2, User = "user2", CategoryID = 2, Description = "Novel", Date = DateTime.Now },
                new Auction { Id = 3, User = "user3", CategoryID = 3, Description = "T-shirt", Date = DateTime.Now }
                // Add more auctions as needed
            );
        }
    }
}
