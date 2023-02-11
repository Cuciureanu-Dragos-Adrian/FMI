using Microsoft.EntityFrameworkCore.Migrations;

namespace api.Migrations
{
    public partial class RemovedCopiesFromGame : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "CopiesAvailable",
                table: "Games");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<int>(
                name: "CopiesAvailable",
                table: "Games",
                type: "int",
                nullable: true);
        }
    }
}
