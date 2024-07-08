using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using Web_practic_travel.Models;

namespace Web_practic_travel.Data
{
    public class ApplicationDbContext : IdentityDbContext
    {
        public DbSet<Flight> flights {  get; set; }
        public DbSet<Hotel> hotels { get; set; }
        public DbSet<Reservation> reservations { get; set; }

        public ApplicationDbContext(DbContextOptions<ApplicationDbContext> options)
            : base(options)
        {
        }
        protected override void OnModelCreating(ModelBuilder modelBuilder)
        {
            base.OnModelCreating(modelBuilder);

            // Seed Flights
            modelBuilder.Entity<Flight>().HasData(
                new Flight { Id = 1, date = "2024/06/20", destinationCity = "New York", availableSeats = 150 },
                new Flight { Id = 2, date = "2024/06/21", destinationCity = "Los Angeles", availableSeats = 200 },
                new Flight { Id = 3, date = "2024/06/22", destinationCity = "Chicago", availableSeats = 180 }
            );

            // Seed Hotels
            modelBuilder.Entity<Hotel>().HasData(
                new Hotel { Id = 1, hotelName = "Grand Hotel", date = "2024/06/20", destinationCity = "New York", availableRooms = 50 },
                new Hotel { Id = 2, hotelName = "Sunset Resort", date = "2024/06/21", destinationCity = "Los Angeles", availableRooms = 70 },
                new Hotel { Id = 3, hotelName = "City Inn", date = "2024/06/22", destinationCity = "Chicago", availableRooms = 40 }
            );

            // Seed Reservations
            modelBuilder.Entity<Reservation>().HasData(
                new Reservation { Id = 1, person = "John Doe", type = "Flight", idReservedResource = 1 },
                new Reservation { Id = 2, person = "Jane Smith", type = "Hotel", idReservedResource = 1 },
                new Reservation { Id = 3, person = "Alice Johnson", type = "Flight", idReservedResource = 2 }
            );
        }
    }
}
