/**
 * @copyright 2018 TwoD
 * @author Brian Cairl
 */

// C++ Standard Library
#include <type_traits>
#include <vector>

// GTest
#include <gtest/gtest.h>

// TwoD
#include <twod/grid.h>
#include <twod/stream.h>


using namespace twod;


TEST(Bounds, Within)
{
  const Bounds bounds{Indices{1, 1}, Extents{5, 5}};

  ASSERT_FALSE(bounds.within(Indices{0, 0}));
  ASSERT_TRUE(bounds.within(Indices{1, 1}));
  ASSERT_TRUE(bounds.within(Indices{5, 5}));
  ASSERT_FALSE(bounds.within(Indices{6, 6}));
}


TEST(Bounds, Overlaps)
{
  const Bounds rbounds{Indices{1, 1}, Extents{5, 5}};
  const Bounds lbounds{Indices{2, 2}, Extents{3, 3}};

  ASSERT_TRUE(rbounds.overlaps(lbounds));
}


TEST(Bounds, OverlapsEdge)
{
  const Bounds rbounds{Indices{1, 1}, Extents{1, 1}};
  const Bounds lbounds{Indices{1, 2}, Extents{3, 3}};

  ASSERT_TRUE(rbounds.overlaps(lbounds));
}


TEST(Bounds, OverlapsCorner)
{
  const Bounds rbounds{Indices{1, 1}, Extents{1, 1}};
  const Bounds lbounds{Indices{2, 2}, Extents{1, 1}};

  ASSERT_TRUE(rbounds.overlaps(lbounds));
}


TEST(FixedExtentsBounds, Within)
{
  const FixedExtentsBounds<5, 5> bounds{Indices{1, 1}};

  ASSERT_FALSE(bounds.within(Indices{0, 0}));
  ASSERT_TRUE(bounds.within(Indices{1, 1}));
  ASSERT_TRUE(bounds.within(Indices{5, 5}));
  ASSERT_FALSE(bounds.within(Indices{6, 6}));
}


TEST(FixedOriginBounds, Within)
{
  const FixedOriginBounds<1, 1> bounds{Extents{5, 5}};

  ASSERT_FALSE(bounds.within(Indices{0, 0}));
  ASSERT_TRUE(bounds.within(Indices{1, 1}));
  ASSERT_TRUE(bounds.within(Indices{5, 5}));
  ASSERT_FALSE(bounds.within(Indices{6, 6}));
}


TEST(FixedOriginExtentsBounds, Within)
{
  const FixedOriginExtentsBounds<1, 1, 5, 5> bounds;

  ASSERT_FALSE(bounds.within(Indices{0, 0}));
  ASSERT_TRUE(bounds.within(Indices{1, 1}));
  ASSERT_TRUE(bounds.within(Indices{5, 5}));
  ASSERT_FALSE(bounds.within(Indices{6, 6}));
}


TEST(Grid, DefaultConstructor)
{
  Grid<int> grid;

  ASSERT_EQ(grid.extents(), Extents::Zero());
  ASSERT_TRUE(grid.empty());
}


TEST(Grid, InitSizeConstructor)
{
  Grid<int> grid{Extents{20, 10}};

  ASSERT_EQ(grid.extents(), (Extents{20, 10}));
  ASSERT_FALSE(grid.empty());
}


TEST(Grid, UniformInitialValueConstructor)
{
  Grid<int> grid{Extents{20, 10}, 1};

  ASSERT_EQ(grid.extents(), (Extents{20, 10}));
  ASSERT_FALSE(grid.empty());

  for (const auto& v : grid)
  {
    ASSERT_EQ(v, 1);
  }
}

TEST(Grid, Resize)
{
  Grid<int> grid{Extents{20, 10}};
  ASSERT_EQ(grid.extents(), (Extents{20, 10}));

  grid.resize(Extents{20, 20});
  ASSERT_EQ(grid.extents(), (Extents{20, 20}));
}


TEST(Grid, ResizeValue)
{
  Grid<int> grid{Extents{20, 10}, 0};
  ASSERT_EQ(grid.extents(), (Extents{20, 10}));

  grid.resize(Extents{20, 20}, 1);
  ASSERT_EQ(grid.extents(), (Extents{20, 20}));

  for (const auto& v : grid)
  {
    ASSERT_EQ(v, 1);
  }
}


TEST(Grid, Within)
{
  const Grid<int> grid{Extents{20, 10}};
  ASSERT_TRUE(grid.within(Indices{1, 1}));
}


TEST(Grid, NotWithin)
{
  const Grid<int> grid{Extents{20, 10}};
  ASSERT_FALSE(grid.within(Indices{21, 11}));
}


TEST(Grid, NonTrivialCell)
{
  Grid<std::vector<int>> grid{Extents{20, 10}};

  ASSERT_EQ(grid.extents(), (Extents{20, 10}));
  ASSERT_FALSE(grid.empty());
}


TEST(Grid, ColViewIterator)
{
  Grid<int> grid{Extents{20, 10}, 1};

  ColViewIterator<Grid<int>> itr{grid};

  for (ColViewIterator<Grid<int>> itr{grid}; itr != ColViewIterator<Grid<int>>{grid, ViewIteratorEnd{}}; ++itr)
  {
    *itr = 5;
  }

  for (ColViewIterator<const Grid<int>> itr{grid}; itr != ColViewIterator<const Grid<int>>{grid, ViewIteratorEnd{}}; ++itr)
  {
    ASSERT_EQ(*itr, 5);
  }
}


TEST(Grid, ColViewIteratorEndTag)
{
  Grid<int> grid{Extents{20, 10}, 1};

  ColViewIterator<Grid<int>> itr{grid};

  for (ColViewIterator<Grid<int>> itr{grid}; itr != ViewIteratorEnd{}; ++itr)
  {
    *itr = 5;
  }

  for (ColViewIterator<const Grid<int>> itr{grid}; itr != ViewIteratorEnd{}; ++itr)
  {
    ASSERT_EQ(*itr, 5);
  }
}


TEST(Grid, RowViewIterator)
{
  Grid<int> grid{Extents{20, 10}, 1};

  RowViewIterator<Grid<int>> itr{grid};

  for (RowViewIterator<Grid<int>> itr{grid}; itr != RowViewIterator<Grid<int>>{grid, ViewIteratorEnd{}}; ++itr)
  {
    *itr = 5;
  }

  for (RowViewIterator<const Grid<int>> itr{grid}; itr != RowViewIterator<const Grid<int>>{grid, ViewIteratorEnd{}}; ++itr)
  {
    ASSERT_EQ(*itr, 5);
  }
}


TEST(Grid, RowViewIteratorEndTag)
{
  Grid<int> grid{Extents{20, 10}, 1};

  RowViewIterator<Grid<int>> itr{grid};

  for (RowViewIterator<Grid<int>> itr{grid}; itr != ViewIteratorEnd{}; ++itr)
  {
    *itr = 5;
  }

  for (RowViewIterator<const Grid<int>> itr{grid}; itr != ViewIteratorEnd{}; ++itr)
  {
    ASSERT_EQ(*itr, 5);
  }
}


TEST(Grid, ViewBoundsIteration)
{
  Grid<int> grid{Extents{20, 10}, 1};

  auto view = grid.view(Bounds{Indices{2, 2}, Extents{5, 5}});

  view.fill(5);
  for (const auto& c : view)
  {
    ASSERT_EQ(c, 5);
  }
}


TEST(GridTraits, CellType)
{
  Grid<int> grid;

  ASSERT_TRUE((std::is_same<GridTraits<decltype(grid)>::cell_type, int>()));
}


TEST(View, FixedOriginExtentsBoundsRangeIteration)
{
  Grid<int> grid{Extents{20, 10}, 1};

  View<Grid<int>, FixedOriginExtentsBounds<2, 2, 3, 3>> view{grid};

  for (auto& c : view)
  {
    c = 5;
  }

  for (const auto& c : view)
  {
    ASSERT_EQ(c, 5);
  }

  for (const auto& c : View<const Grid<int>, FixedOriginExtentsBounds<5, 5, 3, 3>>{grid})
  {
    ASSERT_EQ(c, 1);
  }
}


TEST(View, FixedOriginBoundsRangeIteration)
{
  Grid<int> grid{Extents{20, 10}, 1};

  View<Grid<int>, FixedOriginBounds<2, 2>> view{grid, FixedOriginBounds<2, 2>{Extents{3, 3}}};

  for (auto& c : view)
  {
    c = 5;
  }

  for (const auto& c : view)
  {
    ASSERT_EQ(c, 5);
  }

  for (const auto& c : View<const Grid<int>, FixedOriginBounds<5, 5>>{grid, FixedOriginBounds<5, 5>{Extents{3, 3}}})
  {
    ASSERT_EQ(c, 1);
  }
}


TEST(View, FixedExtentsBoundsRangeIteration)
{
  Grid<int> grid{Extents{20, 10}, 1};

  View<Grid<int>, FixedExtentsBounds<3, 3>> view{grid, FixedExtentsBounds<3, 3>{Indices{2, 2}}};

  for (auto& c : view)
  {
    c = 5;
  }

  for (const auto& c : view)
  {
    ASSERT_EQ(c, 5);
  }

  for (const auto& c : View<const Grid<int>, FixedExtentsBounds<3, 3>>{grid, FixedExtentsBounds<3, 3>{Indices{5, 5}}})
  {
    ASSERT_EQ(c, 1);
  }
}


TEST(View, BoundsRangeIteration)
{
  Grid<int> grid{Extents{20, 10}, 1};

  View<Grid<int>, Bounds> view{grid, Bounds{Indices{2, 2}, Extents{3, 3}}};

  for (auto& c : view)
  {
    c = 5;
  }

  for (const auto& c : view)
  {
    ASSERT_EQ(c, 5);
  }

  for (const auto& c : View<const Grid<int>, Bounds>{grid, Bounds{Indices{5, 5}, Extents{3, 3}}})
  {
    ASSERT_EQ(c, 1);
  }
}


TEST(MappedGrid, FromArrayAssignGrid)
{
  int segment[200];
  std::fill(segment, segment+200, 1);

  MappedGrid<int> grid{Extents{20, 10}, segment};

  grid.view(FixedOriginExtentsBounds<1, 1, 2, 2>{}) = FixedGrid<int, 2, 2>{5};

  EXPECT_EQ((grid[Indices{0, 0}]), 1);
  EXPECT_EQ((grid[Indices{1, 1}]), 5);
  EXPECT_EQ((grid[Indices{1, 2}]), 5);
  EXPECT_EQ((grid[Indices{2, 1}]), 5);
  EXPECT_EQ((grid[Indices{2, 2}]), 5);
  EXPECT_EQ((grid[Indices{3, 3}]), 1);
}


TEST(FixedMappedGrid, FromArrayAssignGrid)
{
  int segment[200];
  std::fill(segment, segment+200, 1);

  FixedMappedGrid<int, 20, 10> grid{segment};

  grid.view(FixedOriginExtentsBounds<1, 1, 2, 2>{}) = FixedGrid<int, 2, 2>{5};

  EXPECT_EQ((grid[Indices{0, 0}]), 1);
  EXPECT_EQ((grid[Indices{1, 1}]), 5);
  EXPECT_EQ((grid[Indices{1, 2}]), 5);
  EXPECT_EQ((grid[Indices{2, 1}]), 5);
  EXPECT_EQ((grid[Indices{2, 2}]), 5);
  EXPECT_EQ((grid[Indices{3, 3}]), 1);
}


TEST(FixedTiledGrid, UniformInitialValueConstructor)
{
  FixedTiledGrid<int, 20, 20, 10, 10> grid{5};

  for (const auto& v : grid)
  {
    ASSERT_EQ(v, 5);
  }
}


TEST(FixedTiledGrid, SingleTileAssign)
{
  FixedTiledGrid<int, 20, 20, 20, 20> grid{5};

  grid[Indices{5, 5}] = 6;

  EXPECT_EQ((grid[Indices{5, 5}]), 6);
}


TEST(FixedTiledGrid, Assign)
{
  FixedTiledGrid<int, 20, 20, 5, 5> grid{5};

  grid[Indices{5, 5}] = 6;
  grid[Indices{18, 19}] = 9;

  ASSERT_TRUE((grid.mask()[Indices{1, 1}]));
  ASSERT_TRUE((grid.mask()[Indices{3, 3}]));
  ASSERT_EQ(grid.active(), 2UL);

  EXPECT_EQ((grid[Indices{5, 5}]), 6);
  EXPECT_EQ((grid[Indices{18, 19}]), 9);
}


TEST(FixedTiledGrid, AssignGrid)
{
  FixedTiledGrid<int, 20, 20, 5, 5> grid{1};

  grid.view(FixedOriginExtentsBounds<1, 1, 2, 2>{}) = FixedGrid<int, 2, 2>{5};

  EXPECT_EQ((grid[Indices{0, 0}]), 1);
  EXPECT_EQ((grid[Indices{1, 1}]), 5);
  EXPECT_EQ((grid[Indices{1, 2}]), 5);
  EXPECT_EQ((grid[Indices{2, 1}]), 5);
  EXPECT_EQ((grid[Indices{2, 2}]), 5);
  EXPECT_EQ((grid[Indices{3, 3}]), 1);
}


// //
// // ASSIGNMENT "STRESS" TESTS
// //


TEST(Grid, AssignIterated)
{
  Grid<int> grid{Extents{2000, 2000}};

  for (auto& c : grid)
  {
    c = 2;
  }
}


TEST(FixedGrid, AssignIterated)
{
  FixedGrid<int, 200, 200> grid{1};

  for (auto& c : grid)
  {
    c = 2;
  }
}


TEST(FixedTiledGrid, AssignIterated)
{
  FixedTiledGrid<int, 2000, 2000, 50, 50> grid{1};

  for (auto& c : grid)
  {
    c = 2;
  }

  ASSERT_EQ(grid.active(), (FixedTiledGrid<int, 2000, 2000, 50, 50>::TileCount));
}


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
