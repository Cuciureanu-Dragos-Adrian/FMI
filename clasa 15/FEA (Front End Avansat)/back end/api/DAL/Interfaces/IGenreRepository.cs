﻿using api.BLL.Models;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Interfaces
{
    public interface IGenreRepository
    {
        Genre GetGenreById(string id);
        List<Genre> GetGenres();
        void Create(GenreWithoutIdModel model);
        void Update(GenreModel model);
        void Delete(string id);
    }
}