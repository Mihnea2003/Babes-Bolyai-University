using Microsoft.AspNetCore.Mvc;
using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.EntityFrameworkCore;
using System;
using System.Linq;
using System.Threading.Tasks;
using Web_practic_auctions.Data;
using Web_practic_auctions.Models;

namespace Web_practic_auctions.Controllers
{
    public class AuctionsController : Controller
    {
        private readonly ApplicationDbContext _context;

        public AuctionsController(ApplicationDbContext context)
        {
            _context = context;
        }

        // GET: Auctions
        public async Task<IActionResult> Index()
        {
            var applicationDbContext = _context.Auctions.Include(a => a.Category);
            return View(await applicationDbContext.ToListAsync());
        }

        // GET: Auctions/Details/5
        public async Task<IActionResult> Details(int? id)
        {
            if (id == null)
            {
                return NotFound();
            }

            var auction = await _context.Auctions
                .Include(a => a.Category)
                .FirstOrDefaultAsync(m => m.Id == id);
            if (auction == null)
            {
                return NotFound();
            }

            return View(auction);
        }

        // GET: Auctions/Create
        public IActionResult Create()
        {
            ViewData["CategoryID"] = new SelectList(_context.Categories, "Id", "Name");
            return View();
        }

        // POST: Auctions/Create
        [HttpPost]
        [ValidateAntiForgeryToken]
        public async Task<IActionResult> Create([Bind("Id,CategoryID,Description")] Auction auction)
        {
            try
            {
                if (ModelState.IsValid)
                {
                    // Retrieve the username from TempData or session
                    string username = TempData["Username"]?.ToString();
                    // Set the 'user' field to the retrieved username
                    auction.User = username;

                    // Set the 'date' field to the current date and time
                    auction.Date = DateTime.Now;

                    // Check if the specified category exists and create it if it doesn't
                    if (!_context.Categories.Any(c => c.Id == auction.CategoryID))
                    {
                        var categoryName = "Default Category"; // You can set the default category name here
                        var category = new Category { Name = categoryName };
                        _context.Categories.Add(category);
                        await _context.SaveChangesAsync();
                        auction.CategoryID = category.Id; // Assign the newly created category ID to the auction
                    }

                    _context.Add(auction);
                    await _context.SaveChangesAsync();
                    return RedirectToAction(nameof(Index));
                }
                ViewData["CategoryID"] = new SelectList(_context.Categories, "Id", "Name", auction.CategoryID);
                return View(auction);
            }
            catch (Exception ex)
            {
                // Log the exception or display an error message
                ModelState.AddModelError(string.Empty, "An error occurred while saving the auction.");
                ViewData["CategoryID"] = new SelectList(_context.Categories, "Id", "Name", auction.CategoryID);
                return View(auction);
            }
        }

        private bool AuctionExists(int id)
        {
            return _context.Auctions.Any(e => e.Id == id);
        }
    }
}
