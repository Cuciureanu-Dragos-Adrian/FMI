﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Genre
    {
        public string Id { get; set; }
        public string Name { get; set; }

        public virtual ICollection<GameGenre> GameGenres { get; set; }
    }
}