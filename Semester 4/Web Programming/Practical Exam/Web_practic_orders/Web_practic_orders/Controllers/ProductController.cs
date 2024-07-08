using Microsoft.AspNetCore.Mvc;
using Microsoft.EntityFrameworkCore;
using Web_practic_orders.Data;
using Web_practic_orders.Models;

namespace Web_practic_orders.Controllers
{
    public class ProductController : Controller
    {
        private readonly ApplicationDbContext _context;

        public ProductController(ApplicationDbContext context)
        {
            _context = context;
        }

        public IActionResult Add()
        {
            return View();
        }

        [HttpPost]
        public async Task<IActionResult> Add(Product product)
        {
            if (ModelState.IsValid)
            {
                _context.Products.Add(product);
                await _context.SaveChangesAsync();
                return RedirectToAction(nameof(Index));
            }
            return View(product);
        }

        public async Task<IActionResult> Index(string searchString)
        {
            var products = from p in _context.Products select p;

            if (!String.IsNullOrEmpty(searchString))
            {
                products = products.Where(s => s.Name.StartsWith(searchString));
            }

            var productList = await products.ToListAsync();

            return View(productList);
        }
    }
}
