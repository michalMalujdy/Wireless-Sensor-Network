using Microsoft.EntityFrameworkCore.Migrations;

namespace Wsn.Data.Migrations
{
    public partial class ChangeValueToState : Migration
    {
        protected override void Up(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "Value",
                table: "LightReadings");

            migrationBuilder.AddColumn<int>(
                name: "State",
                table: "LightReadings",
                nullable: false,
                defaultValue: 0);
        }

        protected override void Down(MigrationBuilder migrationBuilder)
        {
            migrationBuilder.DropColumn(
                name: "State",
                table: "LightReadings");

            migrationBuilder.AddColumn<int>(
                name: "Value",
                table: "LightReadings",
                nullable: false,
                defaultValue: 0);
        }
    }
}
