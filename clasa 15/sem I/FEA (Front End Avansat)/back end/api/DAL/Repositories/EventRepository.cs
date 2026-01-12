using api.BLL.Models;
using api.DAL.Interfaces;
using api.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace api.DAL.Repositories
{
    public class EventRepository : IEventRepository
    {
        private Context db;

        public EventRepository(Context db)
        {
            this.db = db;
        }

        public Event GetEventById(string id)
        {
            var @event = db.Events
                .FirstOrDefault(x => x.Id == id);

            return @event;
        }

        public List<Event> GetEvents()
        {
            var events = db.Events.ToList();

            return events;
        }

        public void Create(EventWithoutIdModel model)
        {
            var newEvent = new Event
            {
                Id = Guid.NewGuid().ToString(),
                Name = model.Name,
                Year = model.Year
            };

            db.Events.Add(newEvent);

            db.SaveChanges();
        }

        public void Update(EventModel model)
        {
            var award = GetEventById(model.Id);

            award.Name = model.Name;
            award.Year = model.Year;

            db.Events.Update(award);

            db.SaveChanges();
        }

        public void Delete(string id)
        {
            var award = GetEventById(id);

            db.Events.Remove(award);

            db.SaveChanges();
        }
    }
}
