using Microsoft.AspNetCore.Mvc.Rendering;
using Microsoft.AspNetCore.Mvc;
using Web_practic_orders.Data;
using Web_practic_orders.Models;
using Microsoft.EntityFrameworkCore;

namespace Web_practic_orders.Controllers
{
    public class OrderController : Controller
    {
        private readonly ApplicationDbContext _context;

        public OrderController(ApplicationDbContext context)
        {
            _context = context;
        }

        public IActionResult CreatePartialOrder()
        {
            ViewData["Products"] = new SelectList(_context.Products, "Id", "Name");
            return View();
        }

        [HttpPost]
        public IActionResult CreatePartialOrder(Order order)
        {
            if (ModelState.IsValid)
            {
                var orders = GetOrdersFromTempData();
                orders.Add(order);
                SetOrdersToTempData(orders);
                return RedirectToAction(nameof(CreatePartialOrder));
            }
            ViewData["Products"] = new SelectList(_context.Products, "Id", "Name", order.ProductId);
            return View(order);
        }

        public IActionResult FinalizeOrder(string username)
        {
            var orders = GetOrdersFromTempData();
            if (orders != null)
            {
                foreach (var order in orders)
                {
                    order.User = username;
                    _context.Orders.Add(order);
                }
                _context.SaveChanges();
                TempData.Remove("Orders");
            }
            return RedirectToAction(nameof(Index), "Product");
        }

        public IActionResult CancelOrder()
        {
            TempData.Remove("Orders");
            return RedirectToAction(nameof(Index), "Product");
        }

        private List<Order> GetOrdersFromTempData()
        {
            var orders = new List<Order>();

            if (TempData["Orders"] != null)
            {
                var ordersString = TempData["Orders"].ToString();
                var orderLines = ordersString.Split('|');

                foreach (var orderLine in orderLines)
                {
                    var orderData = orderLine.Split(',');
                    var order = new Order
                    {
                        ProductId = int.Parse(orderData[0]),
                        Quantity = int.Parse(orderData[1])
                    };
                    orders.Add(order);
                }
            }

            return orders;
        }
        public IActionResult OrderList()
        {
            var orders = _context.Orders.Include(o => o.Product).ToList();
            return View(orders);
        }

        private void SetOrdersToTempData(List<Order> orders)
        {
            var orderStrings = new List<string>();

            foreach (var order in orders)
            {
                var orderString = $"{order.ProductId},{order.Quantity}";
                orderStrings.Add(orderString);
            }

            TempData["Orders"] = string.Join("|", orderStrings);
        }
    }

}
