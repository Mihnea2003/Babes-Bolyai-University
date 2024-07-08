using Microsoft.EntityFrameworkCore.Migrations;

#nullable disable

namespace Examen.Data.Migrations
{
    /// <inheritdoc />
    public partial class InitialSeed2 : Migration
    {
        /// <inheritdoc />
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.InsertData(
                table: "Author",
                columns: new[] { "Id", "Name", "documentList", "movieList" },
                values: new object[] { 2, "Mada", "document,document2", "film,film2" });
        }

        /// <inheritdoc />
        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DeleteData(
                table: "Author",
                keyColumn: "Id",
                keyValue: 2);
        }
    }
}
