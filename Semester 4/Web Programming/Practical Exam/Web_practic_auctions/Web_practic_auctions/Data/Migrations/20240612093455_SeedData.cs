using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

#pragma warning disable CA1814 // Prefer jagged arrays over multidimensional

namespace Web_practic_auctions.Data.Migrations
{
    /// <inheritdoc />
    public partial class SeedData : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "Categories",
                columns: new[] { "Id", "Name" },
                values: new object[,]
                {
                    { 1, "Electronics" },
                    { 2, "Books" },
                    { 3, "Clothing" }
                });

            migrationBuilder.InsertData(
                table: "Auctions",
                columns: new[] { "Id", "CategoryID", "Date", "Description", "User" },
                values: new object[,]
                {
                    { 1, 1, new DateTime(2024, 6, 12, 12, 34, 55, 237, DateTimeKind.Local).AddTicks(3163), "Smartphone", "user1" },
                    { 2, 2, new DateTime(2024, 6, 12, 12, 34, 55, 237, DateTimeKind.Local).AddTicks(3217), "Novel", "user2" },
                    { 3, 3, new DateTime(2024, 6, 12, 12, 34, 55, 237, DateTimeKind.Local).AddTicks(3219), "T-shirt", "user3" }
                });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Auctions",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Auctions",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Auctions",
                keyColumn: "Id",
                keyValue: 3);

            migrationBuilder.DeleteData(
                table: "Categories",
                keyColumn: "Id",
                keyValue: 1);

            migrationBuilder.DeleteData(
                table: "Categories",
                keyColumn: "Id",
                keyValue: 2);

            migrationBuilder.DeleteData(
                table: "Categories",
                keyColumn: "Id",
                keyValue: 3);
        }
    }
}
