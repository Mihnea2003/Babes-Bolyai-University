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
    public class FlightsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public FlightsController(ApplicationDbContext context)
        {
            _context = context;
        }
        [HttpPost]
        [HttpPost]
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Reserve(int id)
        {
            var flight = await _context.flights.FindAsync(id);
            if (flight == null)
            {
                return NotFound();
            }

            if (flight.availableSeats > 0)
            {
                flight.availableSeats--; // Decrement available seats
                _context.Update(flight);
                await _context.SaveChangesAsync();
                string username = TempData["UserName"] as string;
                // Create a new reservation
                var reservation = new Reservation
                {
                    person = username,
                    type = "flight",
                    idReservedResource = flight.Id // Set the flight ID as the reserved resource ID
                };

                // Add the reservation to the context and save changes
                _context.Add(reservation);
                await _context.SaveChangesAsync();
            }

            // Retrieve all flights again after reservation
            var flights = await _context.flights.ToListAsync();

            // Return the view with updated flights
            return View("Index", flights);
        }

        // GET: Flights
        public async Task<IActionResult> Index()
        {
            // Retrieve filter criteria from TempData
            string date = TempData["date"] as string;
            string destination_city = TempData["destination_city"] as string;


            // Query flights based on filter criteria
            var flights = await _context.flights
                .Where(f => f.date == date && f.destinationCity == destination_city && f.availableSeats>0)
                .ToListAsync();

            // Return the view with filtered flights
            return View(flights);
        }
        // GET: Flights/FilterFlights

        // GET: Flights/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var flight = await _context.flights
                .FirstOrDefaultAsync(m => m.Id == id);
            if (flight == null)
            {
                return NotFound();
            }

            return View(flight);
        }

        // GET: Flights/Create
        public IActionResult Create()
        {
            return View();
        }

        // POST: Flights/Create
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,date,destinationCity,availableSeats")] Flight flight)
        {
            if (ModelState.IsValid)
            {
                _context.Add(flight);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(flight);
        }

        // GET: Flights/Edit/5
        public async Task<IActionResult> Edit(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var flight = await _context.flights.FindAsync(id);
            if (flight == null)
            {
                return NotFound();
            }
            return View(flight);
        }

        // POST: Flights/Edit/5
        // To protect from overposting attacks, enable the specific properties you want to bind to.
        // For more details, see http://go.microsoft.com/fwlink/?LinkId=317598.
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Edit(int id, [Bind("Id,date,destinationCity,availableSeats")] Flight flight)
        {
            if (id != flight.Id)
            {
                return NotFound();
            }

            if (ModelState.IsValid)
            {
                try
                {
                    _context.Update(flight);
                    await _context.SaveChangesAsync();
                }
                catch (DbUpdateConcurrencyException)
                {
                    if (!FlightExists(flight.Id))
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
            return View(flight);
        }

        // GET: Flights/Delete/5
        public async Task<IActionResult> Delete(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var flight = await _context.flights
                .FirstOrDefaultAsync(m => m.Id == id);
            if (flight == null)
            {
                return NotFound();
            }

            return View(flight);
        }

        // POST: Flights/Delete/5
        [HttpPost, ActionName("Delete")]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> DeleteConfirmed(int id)
        {
            var flight = await _context.flights.FindAsync(id);
            if (flight != null)
            {
                _context.flights.Remove(flight);
            }

            await _context.SaveChangesAsync();
            return RedirectToAction(nameof(Index));
        }

        private bool FlightExists(int id)
        {
            return _context.flights.Any(e => e.Id == id);
        }
    }
}
