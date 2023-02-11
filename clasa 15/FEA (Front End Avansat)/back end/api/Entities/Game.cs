using Microsoft.EntityFrameworkCore;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class Game
    {
        public string Id { get; set; }
        public string Name { get; set; }
        public string ReleaseDate { get; set; }
        public float? Review { get; set; }
        public float? Price { get; set; }

        public string CompanyId { get; set; }
        public virtual Company Company { get; set; }
        public virtual ICollection<Award> Awards { get; set; }
        public virtual ICollection<GameGenre> GameGenres { get; set; }
    }
}
