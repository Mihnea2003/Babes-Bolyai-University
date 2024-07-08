using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using Web_practic_travel.Data;
using Web_practic_travel.Models;

namespace Web_practic_travel.Controllers
{
    public class HotelsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public HotelsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Hotels
        public async Task<IActionResult> Index()
        {
            // Retrieve filter criteria from TempData
            string date = TempData["date"] as string;
            string destination_city = TempData["destination_city"] as string;


            // Query flights based on filter criteria
            var hotels = await _context.hotels
                .Where(f => f.date == date && f.destinationCity == destination_city)
                .ToListAsync();

            // Return the view with filtered flights
            return View(hotels);
        }
        public async Task<IActionResult> Reserve(int id)
        {
            var hotels = await _context.hotels.FindAsync(id);
            if (hotels == null)
            {
                return NotFound();
            }

            if (hotels.availableRooms > 0)
            {
                hotels.availableRooms--; // Decrement available seats
                _context.Update(hotels);
                await _context.SaveChangesAsync();
                string username = TempData["UserName"] as string;
                // Create a new reservation
                var reservation = new Reservation
                {
                    person = username,
                    type = "hotel",
                    idReservedResource = hotels.Id // Set the flight ID as the reserved resource ID
                };

                // Add the reservation to the context and save changes
                _context.Add(reservation);
                await _context.SaveChangesAsync();
            }

            // Retrieve all flights again after reservation
            var hotel = await _context.hotels.ToListAsync();

            // Return the view with updated flights
            return View("Index", hotel);
        }

        // GET: Hotels/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.hotels
                .FirstOrDefaultAsync(m => m.Id == id);
            if (hotel == null)
            {
                return NotFound();
            }

            return View(hotel);
        }

        // GET: Hotels/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Hotels/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,hotelName,date,destinationCity,availableRooms")] Hotel hotel)
        {
            if (ModelState.IsValid)
            {
                _context.Add(hotel);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(hotel);
        }

        // GET: Hotels/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.hotels.FindAsync(id);
            if (hotel == null)
            {
                return NotFound();
            }
            return View(hotel);
        }

        // POST: Hotels/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,hotelName,date,destinationCity,availableRooms")] Hotel hotel)
        {
            if (id != hotel.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(hotel);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!HotelExists(hotel.Id))
                    {
                        return NotFound();
                    }
                    else
                    {
                        throw;
                    }
                }
                return RedirectToAction(nameof(Index));
            }
            return View(hotel);
        }

        // GET: Hotels/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var hotel = await _context.hotels
                .FirstOrDefaultAsync(m => m.Id == id);
            if (hotel == null)
            {
                return NotFound();
            }

            return View(hotel);
        }

        // POST: Hotels/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var hotel = await _context.hotels.FindAsync(id);
            if (hotel != null)
            {
                _context.hotels.Remove(hotel);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool HotelExists(int id)
        {
            return _context.hotels.Any(e => e.Id == id);
        }
    }
}
