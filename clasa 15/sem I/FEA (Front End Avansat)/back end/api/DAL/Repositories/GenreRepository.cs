using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class GenreRepository : IGenreRepository
    {
        private Context db;

        public GenreRepository(Context db)
        {
            this.db = db;
        }

        public Genre GetGenreById(string id)
        {
            var genre = db.Genres
                .FirstOrDefault(x => x.Id == id);

            return genre;
        }

        public List<Genre> GetGenres()
        {
            var genres = db.Genres.ToList();

            return genres;
        }

        public void Create(GenreWithoutIdModel model)
        {
            var newGenre = new Genre
            {
                Id = Guid.NewGuid().ToString(),
                Name = model.Name
            };

            db.Genres.Add(newGenre);

            db.SaveChanges();
        }

        public void Update(GenreModel model)
        {
            var award = GetGenreById(model.Id);

            award.Name = model.Name;

            db.Genres.Update(award);

            db.SaveChanges();
        }

        public void Delete(string id)
        {
            var award = GetGenreById(id);

            db.Genres.Remove(award);

            db.SaveChanges();
        }
    }
}
