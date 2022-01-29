using api.BLL.Interfaces;
using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.BLL.Managers
{
    public class GenreManager : IGenreManager
    {
        private readonly IGenreRepository repository;

        public GenreManager(IGenreRepository eventRepository)
        {
            this.repository = eventRepository;
        }

        public Genre GetGenreById(string id)
        {
            return repository.GetGenreById(id);
        }

        public List<Genre> GetGenres()
        {
            return repository.GetGenres();
        }

        public void Create(GenreWithoutIdModel model)
        {
            repository.Create(model);
        }

        public void Update(GenreModel model)
        {
            repository.Update(model);
        }

        public void Delete(string id)
        {
            repository.Delete(id);
        }
    }
}
