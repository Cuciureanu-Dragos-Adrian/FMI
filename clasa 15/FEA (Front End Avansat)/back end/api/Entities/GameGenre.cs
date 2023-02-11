using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.Entities
{
    public class GameGenre
    {
        public string GameId { get; set; }
        public string GenreId { get; set; }

        public virtual Game Game { get; set; }
        public virtual Genre Genre { get; set; }
    }
}
