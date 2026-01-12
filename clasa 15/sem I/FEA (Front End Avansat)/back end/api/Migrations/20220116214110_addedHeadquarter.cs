using Microsoft.EntityFrameworkCore.Migrations;

namespace api.Migrations
{
    public partial class addedHeadquarter : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.AddColumn<string>(
                name: "HeadquarterId",
                table: "Companies",
                type: "nvarchar(450)",
                nullable: true);

            migrationBuilder.CreateTable(
                name: "Headquarters",
                columns: table => new
                {
                    Id = table.Column<string>(type: "nvarchar(450)", nullable: false),
                    Continent = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    Country = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    City = table.Column<string>(type: "nvarchar(max)", nullable: true),
                    Street = table.Column<string>(type: "nvarchar(max)", nullable: true)
                },
                constraints: table =>
                {
                    table.PrimaryKey("PK_Headquarters", x => x.Id);
                });

            migrationBuilder.CreateIndex(
                name: "IX_Companies_HeadquarterId",
                table: "Companies",
                column: "HeadquarterId",
                unique: true,
                filter: "[HeadquarterId] IS NOT NULL");

            migrationBuilder.AddForeignKey(
                name: "FK_Companies_Headquarters_HeadquarterId",
                table: "Companies",
                column: "HeadquarterId",
                principalTable: "Headquarters",
                principalColumn: "Id",
                onDelete: ReferentialAction.Restrict);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropForeignKey(
                name: "FK_Companies_Headquarters_HeadquarterId",
                table: "Companies");

            migrationBuilder.DropTable(
                name: "Headquarters");

            migrationBuilder.DropIndex(
                name: "IX_Companies_HeadquarterId",
                table: "Companies");

            migrationBuilder.DropColumn(
                name: "HeadquarterId",
                table: "Companies");
        }
    }
}
