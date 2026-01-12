using Microsoft.EntityFrameworkCore.Migrations;

namespace api.Migrations
{
    public partial class RemovedContinentFromHeadquarter : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Continent",
                table: "Headquarters");
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "Continent",
                table: "Headquarters",
                type: "nvarchar(max)",
                nullable: true);
        }
    }
}
