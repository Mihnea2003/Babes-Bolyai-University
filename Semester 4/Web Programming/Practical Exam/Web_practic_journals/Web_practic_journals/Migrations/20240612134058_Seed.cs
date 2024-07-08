using System;
using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Web_practic_journals.Migrations
{
    /// <inheritdoc />
    public partial class Seed : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 1,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 40, 57, 656, DateTimeKind.Local).AddTicks(3043));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 2,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 40, 57, 656, DateTimeKind.Local).AddTicks(3091));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 3,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 40, 57, 656, DateTimeKind.Local).AddTicks(3093));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 4,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 40, 57, 656, DateTimeKind.Local).AddTicks(3095));
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 1,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 39, 46, 676, DateTimeKind.Local).AddTicks(2255));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 2,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 39, 46, 676, DateTimeKind.Local).AddTicks(2308));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 3,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 39, 46, 676, DateTimeKind.Local).AddTicks(2310));

            migrationBuilder.UpdateData(
                table: "Articles",
                keyColumn: "Id",
                keyValue: 4,
                column: "Date",
                value: new DateTime(2024, 6, 12, 16, 39, 46, 676, DateTimeKind.Local).AddTicks(2312));
        }
    }
}
