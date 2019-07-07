//
// Author: Chiara Bissolotti
//

#pragma once

#include <string>

namespace NangaParbat
{
  /**
   * @brief Preprocessing of the E288 datasets
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessE288(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the E605 datasets
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessE605(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the CDF RunI dataset
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessCDFRunI(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the CDF RunII dataset
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessCDFRunII(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the D0 RunI dataset
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessD0RunI(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the D0 RunII dataset
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessD0RunII(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the LHCb dataset at 7 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessLHCb7TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the LHCb dataset at 8 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessLHCb8TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the LHCb dataset at 13 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessLHCb13TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the CMS dataset at 7 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessCMS7TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the CMS dataset at 8 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessCMS8TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the ATLAS dataset at 7 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessATLAS7TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);

  /**
   * @brief Preprocessing of the ATLAS dataset at 8 TeV
   * @param RawDataPath: the path to the raw-data folder
   * @param ProcessedDataPath: the path to the folder where the processed data will be stored
   * @return the coordinate string
   */
  std::string PreprocessATLAS8TeV(std::string const& RawDataPath, std::string const& ProcessedDataPath);
}
