using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Web_practic_travel.Data.Migrations
{
    /// <inheritdoc />
    public partial class Seeding : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "flights",
                columns: new[] { "Id", "availableSeats", "date", "destinationCity" },
                values: new object[,]
                {
                    { 1, 150, "2024-06-20", "New York" },
                    { 2, 200, "2024-06-21", "Los Angeles" },
                    { 3, 180, "2024-06-22", "Chicago" }
                });

            migrationBuilder.InsertData(
                table: "hotels",
                columns: new[] { "Id", "availableRooms", "date", "destinationCity", "hotelName" },
                values: new object[,]
                {
                    { 1, 50, "2024-06-20", "New York", "Grand Hotel" },
                    { 2, 70, "2024-06-21", "Los Angeles", "Sunset Resort" },
                    { 3, 40, "2024-06-22", "Chicago", "City Inn" }
                });

            migrationBuilder.InsertData(
                table: "reservations",
                columns: new[] { "Id", "idReservedResource", "person", "type" },
                values: new object[,]
                {
                    { 1, 1, "John Doe", "Flight" },
                    { 2, 1, "Jane Smith", "Hotel" },
                    { 3, 2, "Alice Johnson", "Flight" }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "reservations",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "reservations",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "reservations",
                keyColumn: "Id",
                keyValue: 3);
        }
    }
}
