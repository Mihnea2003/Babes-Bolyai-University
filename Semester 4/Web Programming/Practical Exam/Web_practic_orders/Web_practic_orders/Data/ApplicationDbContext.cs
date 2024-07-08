using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_orders.Models;

namespace Web_practic_orders.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Product> Products { get; set; }
        public DbSet<Order> Orders { get; set; }
        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed Products
            modelBuilder.Entity<Product>().HasData(
                new Product { Id = 1, Name = "Product1", Description = "Description for Product1" },
                new Product { Id = 2, Name = "Product2", Description = "Description for Product2" },
                new Product { Id = 3, Name = "Product3", Description = "Description for Product3" }
            );

            // Seed Orders
            modelBuilder.Entity<Order>().HasData(
                new Order { Id = 1, User = "User1", ProductId = 1, Quantity = 2 },
                new Order { Id = 2, User = "User2", ProductId = 2, Quantity = 3 },
                new Order { Id = 3, User = "User1", ProductId = 3, Quantity = 1 }
            );
        }
    }
}
