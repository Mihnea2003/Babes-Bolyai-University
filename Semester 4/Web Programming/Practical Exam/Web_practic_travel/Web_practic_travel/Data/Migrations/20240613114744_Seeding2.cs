using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Web_practic_travel.Data.Migrations
{
    /// <inheritdoc />
    public partial class Seeding2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 1,
                column: "date",
                value: "2024/06/20");

            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 2,
                column: "date",
                value: "2024/06/21");

            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 3,
                column: "date",
                value: "2024/06/22");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 1,
                column: "date",
                value: "2024/06/20");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 2,
                column: "date",
                value: "2024/06/21");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 3,
                column: "date",
                value: "2024/06/22");
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 1,
                column: "date",
                value: "2024-06-20");

            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 2,
                column: "date",
                value: "2024-06-21");

            migrationBuilder.UpdateData(
                table: "flights",
                keyColumn: "Id",
                keyValue: 3,
                column: "date",
                value: "2024-06-22");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 1,
                column: "date",
                value: "2024-06-20");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 2,
                column: "date",
                value: "2024-06-21");

            migrationBuilder.UpdateData(
                table: "hotels",
                keyColumn: "Id",
                keyValue: 3,
                column: "date",
                value: "2024-06-22");
        }
    }
}
