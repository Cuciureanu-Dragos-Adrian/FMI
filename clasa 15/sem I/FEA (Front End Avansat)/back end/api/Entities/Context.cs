using Microsoft.AspNetCore.Identity;
using Microsoft.AspNetCore.Identity.EntityFrameworkCore;
using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Context : IdentityDbContext<User, Role, string, IdentityUserClaim<string>,
        UserRole, IdentityUserLogin<string>, IdentityRoleClaim<string>, IdentityUserToken<string>>
    {
        public Context(DbContextOptions<Context> options) : base(options) { }
        public DbSet<Game> Games { get; set; }
        public DbSet<Company> Companies { get; set; }
        public DbSet<Award> Awards { get; set; }
        public DbSet<Headquarter> Headquarters { get; set; }
        public DbSet<Genre> Genres { get; set; }
        public DbSet<Event> Events { get; set; }
        public DbSet<GameGenre> GameGenres { get; set; }
        public DbSet<CompanyEvent> CompanyEvents { get; set; }


        protected override void OnModelCreating(ModelBuilder builder)
        {
            base.OnModelCreating(builder);

            //One to One
            builder.Entity<Company>()
                .HasOne(company => company.Headquarter)
                .WithOne(headquarter => headquarter.Company)
                .OnDelete(DeleteBehavior.Cascade);

            //One to Many
            builder.Entity<Company>()
                .HasMany(c => c.Games)
                .WithOne(g => g.Company)
                .OnDelete(DeleteBehavior.Cascade);

            builder.Entity<Game>()
                .HasMany(g => g.Awards)
                .WithOne(a => a.Game)
                .OnDelete(DeleteBehavior.Cascade);

            //Many to Many
            builder.Entity<GameGenre>().HasKey(gg => new { gg.GameId, gg.GenreId });

            builder.Entity<GameGenre>()
                .HasOne(gg => gg.Game)
                .WithMany(g => g.GameGenres)
                .HasForeignKey(gg => gg.GameId)
                .OnDelete(DeleteBehavior.Cascade);

            builder.Entity<GameGenre>()
                .HasOne(gg => gg.Genre)
                .WithMany(g => g.GameGenres)
                .HasForeignKey(gg => gg.GenreId)
                .OnDelete(DeleteBehavior.Cascade);


            builder.Entity<CompanyEvent>().HasKey(ce => new { ce.CompanyId, ce.EventId });

            builder.Entity<CompanyEvent>()
                .HasOne(ce => ce.Company)
                .WithMany(c => c.CompanyEvents)
                .HasForeignKey(ce => ce.CompanyId)
                .OnDelete(DeleteBehavior.Cascade);

            builder.Entity<CompanyEvent>()
                .HasOne(ce => ce.Event)
                .WithMany(e => e.CompanyEvents)
                .HasForeignKey(ce => ce.EventId)
                .OnDelete(DeleteBehavior.Cascade);
        }
    }
}
