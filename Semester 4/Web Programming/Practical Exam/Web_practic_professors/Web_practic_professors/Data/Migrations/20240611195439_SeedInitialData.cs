using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Web_practic_professors.Data.Migrations
{
    /// <inheritdoc />
    public partial class SeedInitialData : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "Courses",
                columns: new[] { "Id", "CourseName", "Grades", "Participants", "ProfessorId" },
                values: new object[,]
                {
                    { 1, "Computer Science 101", "2:3,3:4", "2,3", 1 },
                    { 2, "Mathematics 101", "3:5", "3", 1 }
                });

            migrationBuilder.InsertData(
                table: "Persons",
                columns: new[] { "Id", "Name", "Role" },
                values: new object[,]
                {
                    { 1, "Professor John", "professor" },
                    { 2, "Student Alice", "student" },
                    { 3, "Student Bob", "student" }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Courses",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Persons",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Persons",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Persons",
                keyColumn: "Id",
                keyValue: 3);
        }
    }
}
